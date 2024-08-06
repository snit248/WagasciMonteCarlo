// system includes
#include <string>

// BOOST includes
#include <boost/log/trivial.hpp>

// Geant4 includes
#include <G4RunManager.hh>
#include <G4MTRunManager.hh>
#include <G4UIterminal.hh>
#include <G4UItcsh.hh>
#include <QGSP_BERT.hh>
#include <G4VisExecutive.hh>

// project includes
#include "B2Settings.hh"
#include "B2Dimension.hh"
#include "B2Configuration.hh"
#include "B2Logging.hh"
#include "B2DetectorConstruction.hh"
#include "B2PrimaryGeneratorAction.hh"
#include "B2RunAction.hh"
#include "B2EventAction.hh"
#include "B2TrackingAction.hh"
#include "B2Neut.hh"

#ifdef WITH_G4VIS
#include <G4UIQt.hh>
#include <G4UIExecutive.hh>
#endif

#define xstr(a) str(a)
#define str(a) #a

// ====================================================================
//     main
// ====================================================================

int main(int argc, char **argv) {

  preinit_logging();
  B2Configuration configuration(argc, argv, true);
  B2Settings settings = configuration.GetSettings();
  init_logging(settings);

#ifdef VERSION
  if (settings.Has(B2Settings::PrintVersion) && boost::any_cast<bool>(settings.At(B2Settings::PrintVersion))) {
    std::cout << "WAGASCI-BabyMIND Monte Carlo version : " << xstr(VERSION) << std::endl;
    return EXIT_FAILURE;
  }
#endif

  BOOST_LOG_TRIVIAL(info) << "  ************** WAGASCI-BabyMIND Monte Carlo START **************";
  BOOST_LOG_TRIVIAL(info) << "  -- Settings summary --";
  BOOST_LOG_TRIVIAL(info) << settings << std::endl;

  const std::string input_file = boost::any_cast<std::string>(settings.At(B2Settings::InputFilePath));
  const std::string output_file = boost::any_cast<std::string>(settings.At(B2Settings::OutputFilePath));
  const std::string command = boost::any_cast<std::string>(settings.At(B2Settings::Command));

  if (output_file.empty()) {
    BOOST_LOG_TRIVIAL(info) << "Please specify a path for the output root file\n";
    return EXIT_FAILURE;
  }
  if (input_file.empty()) {
    BOOST_LOG_TRIVIAL(info) << "Please select an input NEUT file\n";
    return EXIT_FAILURE;
  }

  auto *run_manager = new G4RunManager;
  // 1. BeginOfRunAction
  // 2. GeneratePrimaries
  // 3. BeginOfEventAction
  // 4. PreUserTrackingAction
  // 5. PostUserTrackingAction
  // 6. EndOfEventAction
  // 7. EndOfRunAction

  try {

    // Neut file reader initialization
    B2Neut neut(input_file);

    BOOST_LOG_TRIVIAL(info) << "Number of events :" << neut.GetEvent().number_events << "\n";

    // singleton object to calculate position of channels
    // Once it is constructed its state must not change
    const B2Dimension dimension(boost::any_cast<std::string>(settings.At(B2Settings::GeometryDirPath)));

    // set mandatory user initialization classes...
    // detector setup
    run_manager->SetUserInitialization(new B2DetectorConstruction(settings, dimension));
    BOOST_LOG_TRIVIAL(info) << "Detector construction : OK\n";
#ifdef NINJA
    BOOST_LOG_TRIVIAL(info) << "Emulsion Sensitive Detector: ON\n";
#else
    BOOST_LOG_TRIVIAL(info) << "Emulsion Sensitive Detector: OFF\n";
#endif

    // particles and physics processes
    run_manager->SetUserInitialization(new QGSP_BERT(0));
    BOOST_LOG_TRIVIAL(info) << "Geant4 Bertini cascade : OK\n";

    auto *p_run_action = new B2RunAction(output_file);
    run_manager->SetUserAction(p_run_action);
    BOOST_LOG_TRIVIAL(info) << "RunAction : OK\n";

    auto *p_event_action = new B2EventAction(p_run_action, dimension, settings);
    run_manager->SetUserAction(p_event_action);
    BOOST_LOG_TRIVIAL(info) << "EventAction : OK\n";

    run_manager->SetUserAction(new B2TrackingAction(p_run_action, settings));
    BOOST_LOG_TRIVIAL(info) << "TrackingAction : OK\n";

    run_manager->SetUserAction(new B2PrimaryGeneratorAction(neut, p_run_action, p_event_action, settings));
    BOOST_LOG_TRIVIAL(info) << "PrimaryGeneratorAction : OK\n";

    // Initialize G4 kernel
    run_manager->Initialize();

    auto *ui = G4UImanager::GetUIpointer();
    ui->ApplyCommand("/run/verbose 0");
    ui->ApplyCommand("/event/verbose 0");
    ui->ApplyCommand("/gps/verbose 0");
    ui->ApplyCommand("/vis/verbose 0");
    ui->ApplyCommand("/analysis/verbose 0");
    ui->ApplyCommand("/hits/verbose 0");
    ui->ApplyCommand("/tracking/verbose 0");
    ui->ApplyCommand("/process/verbose 0");
    ui->ApplyCommand("/process/optical/verbose 0");
    ui->ApplyCommand("/process/had/verbose 0");
    ui->ApplyCommand("/process/em/verbose 0");
    ui->ApplyCommand("/control/verbose 0");

#ifdef WITH_G4VIS
    // initialize visualization package
    auto *vis_manager = new G4VisExecutive("Quiet");
    vis_manager->Initialize();
    bool gui = boost::any_cast<bool>(settings.At(B2Settings::GUI));
    if (gui) {
      auto *session = new G4UIQt(1, &argv[0]);
      if (!command.empty()) {
        std::string execute = "/control/execute " + command;
        ui->ApplyCommand(execute);
      }
      session->SessionStart();
      delete session;
    } else {
#endif
    auto num_requested_spills = boost::any_cast<int>(settings.At(B2Settings::NumberOfSpills));
    const auto num_neut_events = neut.GetEvent().number_events;
    if (!boost::any_cast<bool>(settings.At(B2Settings::CosmicMuons)) &&
        !boost::any_cast<bool>(settings.At(B2Settings::PencilBeam)) &&
	!boost::any_cast<bool>(settings.At(B2Settings::NinjaKinkStudy))){
      //if (num_requested_spills > num_neut_events || num_requested_spills <= 0) {
      num_requested_spills = (int) num_neut_events;
      //}
    }
    run_manager->BeamOn(num_requested_spills);
#ifdef WITH_G4VIS
    }
    delete vis_manager;
#endif

  } catch (const std::runtime_error &error) {
    BOOST_LOG_TRIVIAL(error) << "Program terminated because of runtime error : "
                             << error.what() << "\n";
    return EXIT_FAILURE;
  } catch (const std::invalid_argument &error) {
    BOOST_LOG_TRIVIAL(error) << "Program terminated because of invalid argument : "
                             << error.what() << "\n";
    return EXIT_FAILURE;
  }

  delete run_manager;
  return EXIT_SUCCESS;
}

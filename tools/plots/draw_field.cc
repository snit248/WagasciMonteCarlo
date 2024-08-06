#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <TH2F.h>
#include <TCanvas.h>
#include <TApplication.h>

void mypause() {
  std::cout << "Press [Enter] to continue . . .";
  std::cin.get();
}

void draw_field(const char *magfield_table) {
  std::ifstream data(magfield_table);
  int xbin = 251, ybin = 201;
  double xmin = -2., xmax = 2., ymin = -1.5, ymax = 1.5;
  double pos[3], mag[3];
  TH2F *h[3];
  h[0] = new TH2F("h0", "h0", xbin, xmin, xmax, ybin, ymin, ymax);
  h[1] = new TH2F("h1", "h1", xbin, xmin, xmax, ybin, ymin, ymax);
  h[2] = new TH2F("h2", "h2", xbin, xmin, xmax, ybin, ymin, ymax);
  for (int i = 0; i < 251; i++) {
    for (int j = 0; j < 201; j++) {
      data >> pos[0] >> pos[1] >> pos[2] >> mag[0] >> mag[1] >> mag[2];
      h[0]->SetBinContent(i + 1, j + 1, mag[0]);
      h[1]->SetBinContent(i + 1, j + 1, mag[1]);
      h[2]->SetBinContent(i + 1, j + 1, mag[2]);
    }
  }
  auto *c1 = new TCanvas("c1", "c1");
  c1->Divide(2, 2);
  for (int i = 0; i < 3; i++) {
    c1->cd(i + 1);
    h[i]->GetXaxis()->SetTitle("X (m)");
    h[i]->GetYaxis()->SetTitle("Y (m)");
    h[i]->Draw("colz");
  }
  c1->Update();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage " << argv[0] << " </path/to/magfield.table>\n";
  }
  try {
    TApplication the_app("draw_field", &--argc, &argv[0]);
    draw_field(argv[2]);
    the_app.Run();
  } catch (const std::exception &err) {
    std::cout << "program " << argv[0] << " terminated with error : " << err.what() << "\n";
    std::exit(1);
  }
  mypause();
  std::exit(0);
}



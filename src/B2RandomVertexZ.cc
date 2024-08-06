//
// Created by Giorgio Pintaudi on 8/21/20.
//

#include "B2RandomVertexZ.hh"
#include <Randomize.hh>
#include <G4Types.hh>
#include "B2Const.hh"
#include "B2Enum.hh"
#include "B2Dimension.hh"

B2ProtonModuleScintillatorType B2RandomVertexZ::ProtonModuleRandomTypeOfScintillator() {
  B2ProtonModuleScintillatorType type_of_scintillator =
      G4UniformRand() < PM_SCIBAR_SCINTI_THICK / (PM_INGRID_SCINTI_THICK + PM_SCIBAR_SCINTI_THICK) ?
      kSciBarType : kIngridType;
  return type_of_scintillator;
}

bool B2RandomVertexZ::WagasciRandomVertexZ(TVector3 &interaction_vertex) {
  interaction_vertex.SetZ(WGS_FRAME_START_Z + WGS_WATER_BOX_DEPTH * G4UniformRand());
  return true;
}

//Z position is replaced by X position for WallMRD because the iron plates stand perpendicular to the 
//Z axis of target detectors.

bool B2RandomVertexZ::WallMrdRandomVertexZ(B2Detector detector, TVector3 &interaction_vertex) {
  Int_t have_interaction = false;
  Int_t interaction_layer = (int) (WM_NUM_INNER_IRON_PLANES + WM_NUM_OUTER_IRON_PLANES) * G4UniformRand();
  Double_t position_inside_iron = WM_INNER_IRON_PLATE_THICK * (G4UniformRand() - 0.5);
  Double_t relative_position_x = 0;

  const auto direction = B2Dimension::GetWallMrdDirection(detector);
  if (interaction_layer == 0 || interaction_layer == 10) {
    relative_position_x = (WM_START_IRON_X + WM_PLANES_GAP * interaction_layer) * direction;
    have_interaction = true;
  } else if (interaction_layer < 1 + WM_NUM_INNER_IRON_PLANES) {
    relative_position_x = (WM_START_IRON_X + WM_PLANES_GAP * interaction_layer) * direction;
    have_interaction = true;
  }
  
  interaction_vertex.SetX(relative_position_x + position_inside_iron);
  
  return have_interaction;
}

bool B2RandomVertexZ::BabyMindRandomVertexZ(TVector3 &interaction_vertex) {
  std::size_t interation_plane =
      BM_FIRST_INTERACTION_LAYER +
      std::floor((BM_LAST_INTERACTION_LAYER - BM_FIRST_INTERACTION_LAYER + 1) * G4UniformRand());

  interaction_vertex.SetZ(
      // BabyMIND frame (iron plates) starting point
      // BM_FRAME_START_Z
      // Z coordinate of the interactino point inside the scintillator (randomly generated)
      BM_IRON_PLATE_DEPTH * (G4UniformRand() - 0.5)
      // select the interaction plane
      + BM_IRON_MODULE_Z[interation_plane]
  );

  return true;
}

bool B2RandomVertexZ::NinjaRandomVertexZ(TVector3 &interaction_vertex, B2Material material) {

  bool have_interaction = false;

  switch (material) {
    case B2Material::kWater:
      have_interaction = NinjaWaterRandomVertexZ(interaction_vertex);
      break;
    case B2Material::kIron:
      have_interaction = NinjaIronRandomVertexZ(interaction_vertex);
      break;

    default:
      throw std::invalid_argument("Neutrino interaction material not recognized : " +
                                  std::to_string(material));
  }

  return have_interaction;
}

bool B2RandomVertexZ::NinjaWaterRandomVertexZ(TVector3 &interaction_vertex) {
  G4double lx = interaction_vertex.X() - NINJA_FV_WATER_POS_X;
  G4double ly = interaction_vertex.Y() - NINJA_FV_WATER_POS_Y;
  if (((std::fabs(lx - NINJA_ECC_GAP_X) < 0.5 * NINJA_FV_WATER_WIDTH) ||
       (std::fabs(lx) < 0.5 * NINJA_FV_WATER_WIDTH) ||
       (std::fabs(lx + NINJA_ECC_GAP_X) < 0.5 * NINJA_FV_WATER_WIDTH)) &&
      ((std::fabs(ly - NINJA_ECC_GAP_Y) < 0.5 * NINJA_FV_WATER_HEIGHT) ||
       (std::fabs(ly) < 0.5 * NINJA_FV_WATER_HEIGHT) ||
       (std::fabs(ly + NINJA_ECC_GAP_Y) < 0.5 * NINJA_FV_WATER_HEIGHT))) {
    int interaction_layer = (int) (NINJA_ECC_WATER_LAYERS * G4UniformRand()); // 58 water layers
    G4double posz = NINJA_ECC_POS_Z + 0.5 * NINJA_DESIC_DEPTH
                    - NINJA_DESIC_THICK - 4 * NINJA_ENV_THICK - 17 * NINJA_FILM_THICK
                    - NINJA_SS_AC_THICK - 12 * NINJA_IRON_LAYER_THICK
                    - (NINJA_WATER_LAYER_THICK + NINJA_ECC_UNIT_THICK) * interaction_layer
                    - NINJA_WATER_LAYER_THICK * G4UniformRand();
    interaction_vertex.SetZ(posz);
    return true;
  } else return false;
}

bool B2RandomVertexZ::NinjaIronRandomVertexZ(TVector3 &interaction_vertex) {
  G4double lx = interaction_vertex.X() - NINJA_FV_IRON_POS_X;
  G4double ly = interaction_vertex.Y() - NINJA_FV_IRON_POS_Y;
  if (((std::fabs(lx - NINJA_ECC_GAP_X) < 0.5 * NINJA_FV_IRON_WIDTH) ||
       (std::fabs(lx) < 0.5 * NINJA_FV_IRON_WIDTH) ||
       (std::fabs(lx + NINJA_ECC_GAP_Y) < 0.5 * NINJA_FV_IRON_WIDTH)) &&
      ((std::fabs(ly - NINJA_ECC_GAP_Y) < 0.5 * NINJA_FV_IRON_HEIGHT) ||
       (std::fabs(ly) < 0.5 * NINJA_FV_IRON_HEIGHT) ||
       (std::fabs(ly + NINJA_ECC_GAP_Y) < 0.5 * NINJA_FV_IRON_HEIGHT))) {
    int interaction_layer = (int) (NINJA_ECC_IRON_LAYERS * G4UniformRand()); // 70 iron layers
    G4double posz;
    if (interaction_layer < 11) {
      posz = NINJA_ECC_POS_Z + 0.5 * NINJA_DESIC_DEPTH
             - NINJA_DESIC_THICK - NINJA_ENV_THICK - 4 * NINJA_FILM_THICK - NINJA_SS_AC_THICK
             - (NINJA_IRON_LAYER_THICK + NINJA_FILM_THICK) * interaction_layer
             - NINJA_IRON_LAYER_THICK * G4UniformRand();
    } else {
      posz = NINJA_ECC_POS_Z + 0.5 * NINJA_DESIC_DEPTH
             - NINJA_DESIC_THICK - 3 * NINJA_ENV_THICK - 16 * NINJA_FILM_THICK
             - NINJA_SS_AC_THICK - 11 * NINJA_IRON_LAYER_THICK
             - (NINJA_WATER_LAYER_THICK + NINJA_ECC_UNIT_THICK) * (interaction_layer - 11)
             - NINJA_IRON_LAYER_THICK * G4UniformRand();
    }
    interaction_vertex.SetZ(posz);
    return true;
  } else return false;
}

bool B2RandomVertexZ::WallRandomVertexZ(TVector3 &interaction_vertex) {

  G4double lx = interaction_vertex.X() - WALL_POS_X;
  G4double effective_hall_radius_thick = 3 * m; //corresponding to the "thickness" in the weight calculation
  if (fabs(lx) < HALL_RADIUS_MIN) {
    interaction_vertex.SetZ( -1. * std::sqrt(HALL_RADIUS_MIN * HALL_RADIUS_MIN - lx * lx)
			     - G4UniformRand() * effective_hall_radius_thick );
  } else {
    interaction_vertex.SetZ( -1. * G4UniformRand() * effective_hall_radius_thick );
  }
  return true;
}

bool B2RandomVertexZ::PillarRandomVertexZ(TVector3 &interaction_vertex) {

  interaction_vertex.SetZ(-0.5 * PILLAR_DEPTH + PILLAR_DEPTH * G4UniformRand());
  return true;

}

bool B2RandomVertexZ::ProtonModuleRandomVertexZ(TVector3 &interaction_vertex) {

  double interaction_probability;

  // Enum describing the region of the Proton Module active area where the
  // neutrino interaction occurs
  enum {
    kFrontVeto = 0,
    kSciBarOnlyRegion = 1,
    kMixedVerticalRegion = 2,
    kMixedHorizontalRegion = 3,
    kIngridOnlyRegion = 4
  } vertex_flag;

//  interaction_vertex.Print();
//  // If the interaction happens in the front VETO
//  if (PM_TOTAL_MASS_FRONT_VETO / PM_TOTAL_MASS_SCINTI > G4UniformRand()) {
//    vertex_flag = kFrontVeto;
//    interaction_probability = 1;
//    // Interaction in the inner active area region where there are only INGRID
//    // type scintillator bars
//  } else

  if (std::fabs(interaction_vertex.X()) <= 0.5 * PM_SCIBAR_ACTIVE_AREA_WIDTH &&
      std::fabs(interaction_vertex.Y()) <= 0.5 * PM_SCIBAR_ACTIVE_AREA_HEIGHT) {
    if (PM_VETO_REGION_THICKNESS / (PM_SCIBAR_REGION_THICKNESS + PM_VETO_REGION_THICKNESS) > G4UniformRand()) {
      vertex_flag = kFrontVeto;
    } else {
      vertex_flag = kSciBarOnlyRegion;
    }
    interaction_probability = 1;
  } else if (std::fabs(interaction_vertex.X()) <= 0.5 * PM_SCIBAR_ACTIVE_AREA_WIDTH) {
    if (PM_VETO_REGION_THICKNESS / (PM_MIXED_REGION_THICKNESS + PM_VETO_REGION_THICKNESS) > G4UniformRand()) {
      vertex_flag = kFrontVeto;
    } else {
      vertex_flag = kMixedVerticalRegion;
    }
    interaction_probability = PM_MIXED_REGION_THICKNESS / PM_SCIBAR_REGION_THICKNESS;
  } else if (std::fabs(interaction_vertex.Y()) <= 0.5 * PM_SCIBAR_ACTIVE_AREA_HEIGHT) {
    if (PM_VETO_REGION_THICKNESS / (PM_MIXED_REGION_THICKNESS + PM_VETO_REGION_THICKNESS) > G4UniformRand()) {
      vertex_flag = kFrontVeto;
    } else {
      vertex_flag = kMixedHorizontalRegion;
    }
    interaction_probability = PM_MIXED_REGION_THICKNESS / PM_SCIBAR_REGION_THICKNESS;
  } else {
    if (PM_VETO_REGION_THICKNESS / (PM_INGRID_REGION_THICKNESS + PM_VETO_REGION_THICKNESS) > G4UniformRand()) {
      vertex_flag = kFrontVeto;
    } else {
      vertex_flag = kIngridOnlyRegion;
    }
    interaction_probability = PM_INGRID_REGION_THICKNESS / PM_SCIBAR_REGION_THICKNESS;
  }

  // Because different active area regions in the Proton Module have different
  // mass (when seen the Z direction) we have to reweight the interaction probability
  // The SciBar only region (inner region) has the most mass and is given probability one

  if (interaction_probability < G4UniformRand())
    return false;

  // Calculate the Z coordinate of the vertex

  switch (vertex_flag) {
    case kFrontVeto: {
      // Random integer from 0 to 1 (0 corresponds to the plane 0X and 1 corresponds to the plane 1Y)
      int interaction_plane = (int) (2. * G4UniformRand());
      interaction_vertex.SetZ(
          // Z coordinate of the interaction point inside the scintillator (randomly generated)
          PM_INGRID_SCINTI_THICK * G4UniformRand() +
          // Z coordinate of most upstream surface of the verty first front VETO plane
          PM_FRONT_VETO_START_Z +
          // select the interaction plane (first VETO plane bars are horizontal, second one are vertical)
          interaction_plane * PM_NEXT_PLANE_DISTANCE
      );
      break;
    }
    case kSciBarOnlyRegion: {
      // Random integer from 0 to 33
      // There are 34 scintillator planes in the Z direction in total excluding the front 2 VETO planes
      int interaction_plane = (int) (34. * G4UniformRand());
      interaction_vertex.SetZ(
          // Z coordinate of the interactino point inside the scintillator (randomly generated)
          PM_SCIBAR_SCINTI_THICK * G4UniformRand()
          // Z coordinate of the upstream surface of the 1X plane INGRID bars
          + PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
          // the Z coordinate of the surface of the SciBar bars actually start a little before
          - 0.5 * std::fabs(PM_SCIBAR_SCINTI_THICK - PM_INGRID_SCINTI_THICK)
          // select the interaction plane (0 means the 1X plane, 1 the 1Y, etc)
          + interaction_plane * PM_NEXT_PLANE_DISTANCE
      );
      break;
    }
    case kMixedVerticalRegion: {
      // Random integer from 0 to 16
      // There are 17 planes of SciBar scintillators + 17 planes of INGRID scintillators
      int interaction_plane = (int) (17. * G4UniformRand());
      if (ProtonModuleRandomTypeOfScintillator() == kSciBarType) {
        interaction_vertex.SetZ(
            // Z coordinate of the interaction point inside the scintillator (randomly generated)
            PM_SCIBAR_SCINTI_THICK * G4UniformRand()
            // Z coordinate of the upstream surface of the 1Y plane INGRID bars
            + PM_FRONT_VETO_START_Z + 2 * PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
            // the Z coordinate of the surface of the SciBar bars actually start a little before
            - 0.5 * std::fabs(PM_SCIBAR_SCINTI_THICK - PM_INGRID_SCINTI_THICK)
            // select the interaction plane (0 means the 1Y plane, 1 the 2Y, etc). INGRID bars are skipped.
            + interaction_plane * PM_NEXT_PLANE_DISTANCE * 2
        );
      } else {
        interaction_vertex.SetZ(
            // Z coordinate of the interaction point inside the scintillator (randomly generated)
            PM_INGRID_SCINTI_THICK * G4UniformRand()
            // Z coordinate of the upstream surface of the 1X plane INGRID bars
            + PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
            // select the interaction plane (0 means the 1X plane, 1 the 2X, etc). SciBar bars are skipped.
            + interaction_plane * PM_NEXT_PLANE_DISTANCE * 2
        );
      }
      break;
    }
    case kMixedHorizontalRegion: {
      // Random integer from 0 to 16
      // There are 17 planes of SciBar scintillators + 17 planes of INGRID scintillators
      int interaction_plane = (int) (17. * G4UniformRand());
      if (ProtonModuleRandomTypeOfScintillator() == kSciBarType) {
        interaction_vertex.SetZ(
            // Z coordinate of the interaction point inside the scintillator (randomly generated)
            PM_SCIBAR_SCINTI_THICK * G4UniformRand()
            // Z coordinate of the upstream surface of the 1X plane INGRID bars
            + PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
            // the Z coordinate of the surface of the SciBar bars actually start a little before
            - 0.5 * std::fabs(PM_SCIBAR_SCINTI_THICK - PM_INGRID_SCINTI_THICK)
            // select the interaction plane (0 means the 1X plane, 1 the 2X, etc). INGRID bars are skipped.
            + interaction_plane * PM_NEXT_PLANE_DISTANCE * 2
        );
      } else {
        interaction_vertex.SetZ(
            // Z coordinate of the interaction point inside the scintillator (randomly generated)
            PM_INGRID_SCINTI_THICK * G4UniformRand()
            // Z coordinate of the upstream surface of the 1Y plane INGRID bars
            + PM_FRONT_VETO_START_Z + PM_0Y_1X_PLANE_DISTANCE + 2 * PM_NEXT_PLANE_DISTANCE
            // select the interaction plane (0 means the 1Y plane, 1 the 2Y, etc). SciBar bars are skipped.
            + interaction_plane * PM_NEXT_PLANE_DISTANCE * 2
        );
      }
      break;
    }
    case kIngridOnlyRegion: {
      // Random integer from 0 to 33
      // There are 34 scintillator planes in the Z direction in total excluding the front 2 VETO planes
      int interaction_plane = (int) (34. * G4UniformRand());
      interaction_vertex.SetZ(
          // Z coordinate of the interaction point inside the scintillator (randomly generated)
          PM_INGRID_SCINTI_THICK * G4UniformRand()
          // Z coordinate of the upstream surface of the 1X plane INGRID bars
          + PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
          // select the interaction plane (0 means the 1X plane)
          + interaction_plane * PM_NEXT_PLANE_DISTANCE
      );
      break;
    }
  }
  return true;
}

bool B2RandomVertexZ::GenerateRandomVertexZ(B2Detector detector, TVector3 &interaction_vertex, B2Material material) {
  bool have_interaction = false;
  switch (detector) {
    // vertex in Proton Module scintillators
    case B2Detector::kProtonModule:
      if (std::fabs(interaction_vertex.X()) <= 0.5 * PM_TOTAL_ACTIVE_AREA_WIDTH &&
          std::fabs(interaction_vertex.Y()) <= 0.5 * PM_TOTAL_ACTIVE_AREA_HEIGHT) {
        have_interaction = ProtonModuleRandomVertexZ(interaction_vertex);
      }
      break;
      // vertex in WAGASCI water and scintillators
    case B2Detector::kWagasciUpstream:
    case B2Detector::kWagasciDownstream:
      if (std::fabs(interaction_vertex.X()) <= 0.5 * WGS_WATER_BOX_WIDTH &&
          std::fabs(interaction_vertex.Y()) <= 0.5 * WGS_WATER_BOX_HEIGHT) {
        have_interaction = WagasciRandomVertexZ(interaction_vertex);
      }
      break;
      // vertex in Wide-MRD iron and scintillators (only active area covered by the scintillators)
    case B2Detector::kWallMrdSouth:
    case B2Detector::kWallMrdNorth:
      //WallMRD should be rotated in creating vertex. So X should be switched to Z
      if (std::fabs(interaction_vertex.Z()) <= 0.5 * WM_INNER_FRAME_DEPTH &&
          std::fabs(interaction_vertex.Y()) <= 0.5 * WM_INNER_FRAME_HEIGHT) {
        have_interaction = WallMrdRandomVertexZ(detector, interaction_vertex);
      }
      break;
      // vertex in the iron plates of BabyMIND
    case B2Detector::kBabyMind:
      if (std::fabs(interaction_vertex.X()) <= 0.5 * BM_IRON_PLATE_WIDTH &&
          std::fabs(interaction_vertex.Y()) <= 0.5 * BM_IRON_PLATE_HEIGHT) {
        have_interaction = BabyMindRandomVertexZ(interaction_vertex);
      }
      break;
      // vertex in NINJA
    case B2Detector::kNinja:
      have_interaction = NinjaRandomVertexZ(interaction_vertex, material);
      break;
      // Vertex in B2 floor circular concrete wall // TODO
    case B2Detector::kWall:
      have_interaction = WallRandomVertexZ(interaction_vertex);
      break;
      // Vertex in B2 pillar // TODO
    case B2Detector::kPillarSouth:
    case B2Detector::kPillarNorth:
      if (std::fabs(interaction_vertex.X()) <= 0.5 * PILLAR_WIDTH &&
          std::fabs(interaction_vertex.Y()) <= 0.5 * PILLAR_HEIGHT) {
        have_interaction = PillarRandomVertexZ(interaction_vertex);
      }
      break;
      // Vertex in B2 floor // TODO

    default:
      throw std::invalid_argument("Neutrino interaction module not recognized : " +
                                  std::to_string(detector));
  }
  return have_interaction;
}

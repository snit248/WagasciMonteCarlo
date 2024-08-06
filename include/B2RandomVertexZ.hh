//
// Created by Giorgio Pintaudi on 8/21/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2RANDOMVERTEXZ_HH
#define WAGASCIBABYMINDMONTECARLO_B2RANDOMVERTEXZ_HH

#include <TVector3.h>
#include "B2Const.hh"
#include "B2Enum.hh"

class B2RandomVertexZ {

public:

  /**
   * Randomly select the Z coordinate of the interaction vertex)
   *
   * @param detector detector ID
   * @param interaction_vertex interaction vertex (only the Z coordinate is modified)
   * @param material material where the vertex is generated
   * @return true if the interaction happens, false if the interaction must be discarded
   */
  static bool GenerateRandomVertexZ(B2Detector detector, TVector3 &interaction_vertex,
                                    B2Material material = B2Material::kUnknownMaterial);

private:

  /**
   * @return select randomly between SciBar type of scintillator and INGRID type of
   * scintillator based on the relative depth in the Z direction
   */
  static B2ProtonModuleScintillatorType ProtonModuleRandomTypeOfScintillator();


  /**
  * Randomly select the Z coordinate of the interaction vertex in Proton Module
  *
  * @param interaction_vertex interaction vertex (only the Z coordinate is modified)
  * @return true if the interaction happens, false if the interaction must be discarded
  */
  static bool ProtonModuleRandomVertexZ(TVector3 &interaction_vertex);

  /**
   * Randomly select the Z coordinate of the interaction vertex in WAGASCI upstream or
   * downstream
   *
   * @param interaction_vertex interaction vertex (only the Z coordinate is modified)
   * @return true if the interaction happens, false if the interaction must be discarded
   */
  static bool WagasciRandomVertexZ(TVector3 &interaction_vertex);

  /**
   * Randomly select the Z coordinate of the interaction vertex in WallMRD north or south
   *
   * @param interaction_vertex interaction vertex (only the Z coordinate is modified)
   * @return true if the interaction happens, false if the interaction must be discarded
   */
  static bool WallMrdRandomVertexZ(B2Detector detector,TVector3 &interaction_vertex);

  /**
   * Randomly select the Z coordinate of the interaction vertex in BabyMIND
   *
   * @param interaction_vertex interaction vertex (only the Z coordinate is modified)
   * @return true if the interaction happens, false if the interaction must be discarded
   */
  static bool BabyMindRandomVertexZ(TVector3 &interaction_vertex);

  /**
   * Randomly select the Z coordinate of the interaction vertex in the concrete walls
   *
   * @param interaction_vertex interaction vertex (only the Z coordinate is modified)
   * @return true if the interaction happens, false if the interaction must be discarded
   */
  static bool WallRandomVertexZ(TVector3 &interaction_vertex);

  /**
   * Randomly select the Z coordinate of the interaction vertex in the concrete pillar
   *
   * @param interaction_vertex interaction vertex (only the Z coordinate is modified)
   * @return true if the interaction happens, false if the interaction must be discarded
   */
  static bool PillarRandomVertexZ(TVector3 &interaction_vertex);

  /**
   * Randomly select the Z coordinate of the interaction vertex in NINJA
   *
   * @param interaction_vertex interaction vertex (only the Z coordinate is modified)
   * @param material interaction material in the NINJA ECCs (water/iron)
   * @return true if the interaction happens, false if the interaction must be discarded
   */
  static bool NinjaRandomVertexZ(TVector3 &interaction_vertex, B2Material material);


  /**
   * Randomly select the Z coordinate of the interaction bertex in NINJA water layers
   *
   * @param interaction_vertex interaction vertex (only the Z coordinate is modified)
   * @return true if the interaction happens, false if the inteaction must be discarded
   */
  static bool NinjaWaterRandomVertexZ(TVector3 &interaction_vertex);

  /**
   * Randomly select the Z coordinate of the interaction bertex in NINJA iron layers
   *
   * @param interaction_vertex interaction vertex (only the Z coordinate is modified)
   * @return true if the interaction happens, false if the inteaction must be discarded
   */
  static bool NinjaIronRandomVertexZ(TVector3 &interaction_vertex);

};


#endif //WAGASCIBABYMINDMONTECARLO_B2RANDOMVERTEXZ_HH

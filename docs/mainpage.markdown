The output of a Monte Carlo simulation run comes in the form of a ROOT TFile, that contains
two TTrees:
- `tree` : main TTree with hits, tracks, vertices, etc.. information
- `h1` : NEUT input summary only useful for T2Kreweight (not yet implemented)

In principle, any bit of information useful for the cross-section analysis in included 
in the output TTree. 

## Why a new data format?

The output data format was developed to address the following issues:

- To be compatible with all subdetectors: WAGASCI, WallMRD, Proton Module and BabyMIND
- To accomodate single readout scintillators and double readout scintillators
- To be able to store every measurable quantity together with its error
- To have the least amount of redundancy without sacrificing clarity
- To have clear and descripting variables names (no more NEUT gibberish)
- To have easy to read using the WAGASCI library
- To be able to store Michel electrons and the associated vertex
- Each spill can contain multiple neutrino events (from same or different bunches)

In order to achieve these requirements we had to give up something. Here are some unavoidable 
side effects of the new data format.

- It is not meant to be easily used in the ROOT command line
- It is not optimized for aggressive space saving. It still has some redundancy.
- It has no support for INGRID module

## Points to keep in mind

Some things to keep in mind when using the new data format:

- Each leaf of the main branch corresponds to a single spill (B2SpillSummary class).
- Each spill can contain multiple events (B2EventSummary class).
- In the current version of the MC there is only one event per spill. However this might not be true for the real data.
- There is only a primary vertex (B2VertexSummary class) per event, pointed by the event `primary_vertex_` reference.
- There might be multiple secondary vertices (for example Michel electron, etc...) for one event.
- Some information about the primary vertex is contained in the B2EventSummary too. This redundancy could come useful 
if you just want to quickly select events based on some generic information about the primary particle.

## Schema

Here is a complete description of the `tree` structure:

\image html images/TTree.png width=1280px
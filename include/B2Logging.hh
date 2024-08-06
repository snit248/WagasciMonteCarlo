//
// Created by Giorgio Pintaudi on 7/10/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_LOGGING_HPP
#define WAGASCIBABYMINDMONTECARLO_LOGGING_HPP

#include "B2Settings.hh"

/**
 * Function to pre-initialize BOOST logger
 */
void preinit_logging();

/**
 * Function to initialize BOOST logger
 */
void init_logging(const B2Settings &settings);

#endif //WAGASCIBABYMINDMONTECARLO_LOGGING_HPP

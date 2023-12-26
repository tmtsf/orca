#include "aad/number.hpp"
#include "aad/tape.hpp"

namespace orca { namespace aad {
  Tape theTape;

  thread_local tape_ptr_t Number::m_Tape = &theTape;
}}

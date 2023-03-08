#include "frame.h"

namespace shooter {

void update_frame(Frame* frame) {
  auto prev = frame->cur_msec;
  frame->cur_msec = SDL_GetTicks64();
  frame->prev_msec = prev;
  ++frame->frame_count;
}

}  // namespace shooter

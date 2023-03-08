#pragma once

namespace shooter {

/// @brief フレーム情報
struct Frame {
  Uint64 prev_msec = 0;
  Uint64 cur_msec = 0;
  Uint64 frame_count = 0;

  Uint64 delta_msec() const { return cur_msec - prev_msec; }
  float delta_sec() const { return delta_msec() / 1000.0f; }
};

/// @brief フレーム更新
/// @param [in,out] frame
void update_frame(Frame* frame);

}  // namespace shooter

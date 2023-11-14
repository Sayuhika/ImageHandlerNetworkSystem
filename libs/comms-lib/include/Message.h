#pragma once

#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>
#include <bitsery/brief_syntax.h>
#include <bitsery/brief_syntax/string.h>
#include <bitsery/brief_syntax/vector.h>
#include <cstdint>
#include <string>
#include <vector>

using OutputAdapter = bitsery::OutputBufferAdapter<std::string>;
using InputAdapter = bitsery::InputBufferAdapter<std::string>;

struct Image 
{
  unsigned width;
  unsigned height;

  std::vector<uint8_t> color_channel_r;
  std::vector<uint8_t> color_channel_g;
  std::vector<uint8_t> color_channel_b;

  template <typename S> void serialize(S &s) { s(width, height, color_channel_r, color_channel_g, color_channel_b); }
};

struct AoiMsg
{
  std::string time;
  std::vector<Image> aoi; ///< array of images
  
  template <typename S> void serialize(S &s) { s(time, aoi); }
};

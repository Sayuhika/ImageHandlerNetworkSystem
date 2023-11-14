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

  std::vector<uint8_t> image_channel_r;
  std::vector<uint8_t> image_channel_g;
  std::vector<uint8_t> image_channel_b;

  template <typename S> void serialize(S &s) { s(width, height, image_channel_r, image_channel_g, image_channel_b); }
};

struct MSG 
{
  Image img1;
  Image img2;
  
  std::string time;

  template <typename S> void serialize(S &s) { s(img1, img2, time); }
};

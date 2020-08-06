#include "band/asset/font/helvetica.font.h"

#include <array>
#include <cstdint>

namespace band {
namespace asset {
namespace font {

namespace {


}  // namespace

band::File Helvetica() {
  return band::File{
    .bytes = kHelveticaBytes.data(),
    .n = 317968
  };
}

}  // namespace band
}  // namespace asset
}  // namespace font
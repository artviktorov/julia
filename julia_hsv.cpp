#include <complex>
#include <fstream>
#include <iostream>
#include <cassert>
#include <tuple>
#include <cmath>

constexpr int w = 800;
constexpr int h = 800;
constexpr double re_min = -1.2;
constexpr double im_min = -1.2;
constexpr double re_max = 1.2;
constexpr double im_max = 1.2;
constexpr std::complex<double> c(0.285, 0.01);
constexpr int iter = 90;

std::complex<double> point2c(double x, double y) {
  double re = x * (re_max - re_min) / w + re_min;
  double im = y * (im_max - im_min) / h + im_min;
  return {re, im};
}

std::tuple<int, int, int> hsv2rgb(double hue, double saturation, double value) {
  double c = value * saturation;
  double h2 = hue / 60.f;
  double x = c * (1 - fabs(fmod(h2, 2) - 1));
  double r = 0, g = 0, b = 0;
  if (h2 >= 0 && h2 < 1)
    r = c, g = x, b = 0;
  else if (h2 >= 1 && h2 < 2)
    r = x, g = c, b = 0;
  else if (h2 >= 2 && h2 < 3)
    r = 0, g = c, b = x;
  else if (h2 >= 3 && h2 < 4)
    r = 0, g = x, b = c;
  else if (h2 >= 4 && h2 < 5)
    r = x, g = 0, b = c;
  else if (h2 >= 5 && h2 < 6)
    r = c, g = 0, b = x;
  double m = value - c;
  return {static_cast<int>((r + m) * 255),
          static_cast<int>((g + m) * 255),
          static_cast<int>((b + m) * 255)};
}

int main() {
  std::ofstream img("img.ppm");
  assert(img.is_open() && "Could not open image file.");
  img << "P3\n" << w << " " << h << "\n255\n";

  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      auto z = point2c(x, y);
      int i = 0;
      for (; i < iter; ++i) {
        if (abs(z) >= 2.f) break;
        z = z * z + c;
      }
      
      double hue = i * 360.f / iter;
      double saturation = 1.f;
      double value = i < iter ? 1.f : 0.f;

      auto [r, g, b] = hsv2rgb(hue, saturation, value);
      img << r << " " << g << " " << b << " ";
    }
    img << "\n";
  }

  img.close();

  return 0;
}

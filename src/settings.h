#include <boost/multiprecision/cpp_dec_float.hpp>
using BigFloat = boost::multiprecision::cpp_dec_float_50;

inline constexpr int
    FPS = 60,
    ITER = 200
;

inline const BigFloat
    WIDTH = 800,
    HEIGHT = 800,
    REAL_MIN = -2,
    REAL_MAX = 2,
    IMG_MIN = -2,
    IMG_MAX = 2,
    ZOOM_STEP = 0.05
;

inline constexpr float
    // pink: 0.76f
    // light blue: 0.5f
    // green: 0.32f
    // yellow: 0.14f
    // orange:0.04f
    // red: 0.0f

    TINT = 0.64f,
    TINT_STEP = 0.02f
;

inline constexpr char
    TITLE[] = "Mandelbrot Set"
;
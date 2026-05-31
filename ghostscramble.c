#include <stdint.h>

struct ghostscramble64_state {
  uint64_t a;
  uint64_t b;
  uint64_t c;
};

struct ghostscramble128_state {
  uint64_t output[2];
  uint64_t a;
  uint64_t b;
  uint64_t c;
};

struct ghostscramble256_state {
  uint64_t output[4];
  uint64_t a;
  uint64_t b;
  uint64_t c;
  uint64_t d;
};

uint64_t ghostscramble64(struct ghostscramble64_state *s) {
  s->a = ((s->a << 29) | (s->a >> 35)) ^ s->b;
  s->b += 1111111111111111;
  s->c = ((s->c << 41) | (s->c >> 23)) + s->a;
  return s->c;
}

void ghostscramble128(struct ghostscramble128_state *s) {
  s->a = ((s->a << 29) | (s->a >> 35)) ^ s->b;
  s->b += 11111111111111111;
  s->output[0] = s->a + s->c;
  s->c = ((s->c << 43) | (s->c >> 21)) + s->a;
  s->output[1] = (s->a + s->b) ^ s->c;
}

void ghostscramble256(struct ghostscramble256_state *s) {
  s->a = ((s->a << 29) | (s->a >> 35)) ^ s->b;
  s->b += 111111111111111111;
  s->output[0] = s->a + s->c;
  s->c = ((s->c << 47) | (s->c >> 17)) + s->a;
  s->output[1] = (s->a + s->b) ^ s->c;
  s->output[2] = s->a ^ s->d;
  s->d = ((s->d << 25) | (s->d >> 39)) + s->a;
  s->output[3] = s->a + ((s->d << 23) | (s->d >> 41));
}

let config = (~duration, ~damping) => {
  let (zeta, omega, clamp) =
    if (1. -. damping < 0.001) {
      (
        /* critically damped */
        /* https://electronics.stackexchange.com/a/296698 */
        1.,
        5.8335 /. duration,
        true /* TODO: not sure if clamp needs to be set here */
      );
    } else {
      (
        /* underdamped */
        /* derived using */
        /* https://en.wikipedia.org/wiki/Mass-spring-damper_model */
        /* https://en.wikipedia.org/wiki/Settling_time */
        damping,
        -. log(0.02) /. (damping *. duration),
        false,
      );
    };

  let tension = omega ** 2.;
  let friction = 2. *. zeta *. omega;
  Spring.config(~mass=1., ~tension, ~friction, ~clamp);
};
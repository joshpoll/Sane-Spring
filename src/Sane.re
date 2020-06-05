[@bs.val] external pi: float = "Math.PI";

let eps = 0.001;

let config = (~duration, ~damping) =>
  /* mass is always 1 */
  /* zeta is damping ratio = c / (2*sqrt(k)) = c / (2*omega0) */
  /* omega0 is undamped angular frequency/natural frequency = sqrt(k) */
  if (duration < eps) {
    Spring.config(~mass=1., ~tension=0., ~friction=0., ~clamp=true);
  } else {
    let (zeta, omega, clamp) =
      if (1. -. damping < eps) {
        (
          /* critically damped */
          /* https://electronics.stackexchange.com/a/296698 */
          1.,
          5.8335 /. duration,
          true /* TODO: not sure if clamp needs to be set here */
        );
      } else if (damping < eps) {
        (
          /* not damped */
          /* duration means period */
          /* omega = 2 * pi / duration */
          0.,
          2. *. pi /. duration,
          false,
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
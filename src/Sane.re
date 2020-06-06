[@bs.val] external pi: float = "Math.PI";

let eps = 0.001;

/*   noWobble: { stiffness: 170, damping: 26 }, // the default, if nothing provided
     gentle: { stiffness: 120, damping: 14 },
     wobbly: { stiffness: 180, damping: 12 },
     stiff: { stiffness: 210, damping: 20 }, */

/* c/(2*sqrt(k)) */

/* damping, duration */
let noWobble = (1, 0.4474);
let gentle = (0.6390, 0.5589);
let wobbly = (0.4472, 0.6520);
let stiff = (0.6901, 0.3912);

let config = (~duration, ~damping) =>
  /* mass is always 1 */
  /* zeta is damping ratio = c / (2*sqrt(k)) = c / (2*omega0) */
  /* omega0 is undamped angular frequency/natural frequency = sqrt(k) */
  if (duration < eps) {
    /* TODO: should just teleport to destination */
    /* TODO: or maybe ban this */
    Spring.config(
      ~mass=1.,
      ~tension=0.,
      ~friction=0.,
      ~clamp=true,
    );
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
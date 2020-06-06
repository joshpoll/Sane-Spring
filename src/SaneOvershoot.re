/* uses overshoot instead of damping */

[@bs.val] external pi: float = "Math.PI";

/* https://electronics.stackexchange.com/a/296698 */
/* https://en.wikipedia.org/wiki/Mass-spring-damper_model */
/* https://en.wikipedia.org/wiki/Settling_time */
/* https://ocw.mit.edu/courses/mechanical-engineering/2-004-dynamics-and-control-ii-spring-2008/lecture-notes/lecture_21.pdf */
let eps = 0.001;

/*   noWobble: { stiffness: 170, damping: 26 }, // the default, if nothing provided
     gentle: { stiffness: 120, damping: 14 },
     wobbly: { stiffness: 180, damping: 12 },
     stiff: { stiffness: 210, damping: 20 }, */

let config = (~duration, ~overshoot) =>
  /* mass is always 1 */
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
    let (omega, friction) =
      if (overshoot < eps) {
        /* critically damped */
        let omega = 5.8335 /. duration;
        (omega, 2. *. omega);
      } else if (1. -. overshoot < eps) {
        (
          /* not damped */
          /* duration means period */
          2. *. pi /. duration,
          0.,
        );
      } else {
        /* underdamped */
        let logOS = log(overshoot);
        let zeta = -. logOS /. sqrt(pi ** 2. +. logOS ** 2.);
        let omega = -. log(0.02) /. (duration *. zeta);
        (omega, 2. *. zeta *. omega);
      };

    let tension = omega ** 2.;
    Spring.config(~mass=1., ~tension, ~friction, ~clamp=false);
  };
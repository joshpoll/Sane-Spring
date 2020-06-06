type stage =
  | Before
  | After;

module SpringHook =
  Spring.MakeSpring({
    type t = (float, float, float);
    type interpolate = (float, float, float) => string;
  });

let trans = (x, y, s) => {j|translate($(x)px, $(y)px) scale($s)|j};

[@react.component]
let make = (~duration, ~overshoot, ~prevStage, ~stage) => {
  let start =
    switch (prevStage) {
    | Before => (0., 0., 1.)
    | After => (150., 0., 1.)
    };
  let stop =
    switch (stage) {
    | Before => (0., 0., 1.)
    | After => (150., 0., 1.)
    };
  /* let (start, stop) =
     switch (stage) {
     | Before => ((0., 0., 1.), (150., 0., 1.))
     | After => ((150., 0., 1.), (0., 0., 1.))
     }; */

  let (values, setValues) =
    SpringHook.use(~config=SaneOvershoot.config(~duration, ~overshoot), start);

  let _ = setValues(~config=SaneOvershoot.config(~duration, ~overshoot), stop);

  <svg width="500">
    // onMouseDown={e => {}}
    // onMouseLeave={() => setValues((0., 0., 1.))}

      <SpringHelper.G
        style={ReactDOMRe.Style.make(~transform=values->SpringHook.interpolate(trans), ())}>
        <circle cx="100" cy="100" r="40" stroke="black" strokeWidth="3" fill="red" />
      </SpringHelper.G>
      <rect x="100" y="100" width="225" height="10" fill="blue" />
      <rect x="100" y="100" width="187.5" height="10" fill="orange" />
      <rect x="100" y="100" width="150" height="10" />
    </svg>;
};
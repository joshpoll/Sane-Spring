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
let make = (~duration, ~damping, ~prevStage, ~stage) => {
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

  let (values, setValues) = SpringHook.use(~config=Sane.config(~duration, ~damping), start);

  let _ = setValues(~config=Sane.config(~duration, ~damping), stop);

  <svg width="500">
    // onMouseDown={e => {}}
    // onMouseLeave={() => setValues((0., 0., 1.))}

      <SpringHelper.G
        style={ReactDOMRe.Style.make(~transform=values->SpringHook.interpolate(trans), ())}>
        <circle cx="100" cy="100" r="40" stroke="black" strokeWidth="3" fill="red" />
      </SpringHelper.G>
    </svg>;
};
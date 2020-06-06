[@react.component]
let make = () => {
  let (duration, changeDuration) = React.useState(() => 1.5);
  let (overshoot, changeOvershoot) = React.useState(() => 0.);
  let ((prevStage, stage), changeStages) =
    React.useState(() => (BallOvershoot.Before, BallOvershoot.Before));

  <>
    <h2> {React.string("duration (sec)")} </h2>
    <input
      type_="number"
      value={Js.Float.toString(duration)}
      onChange={key_event => {
        let newinput = key_event->ReactEvent.Form.target##value;
        changeDuration(_ => float_of_string(newinput));
      }}
    />
    <input
      type_="range"
      min="0"
      max="3"
      value={Js.Float.toString(duration)}
      step=0.1
      onChange={key_event => {
        let newinput = key_event->ReactEvent.Form.target##value;
        changeDuration(_ => float_of_string(newinput));
      }}
    />
    <h2> {React.string("overshoot")} </h2>
    <input
      type_="number"
      value={Js.Float.toString(overshoot)}
      onChange={key_event => {
        let newinput = key_event->ReactEvent.Form.target##value;
        changeOvershoot(_ => float_of_string(newinput));
      }}
    />
    <input
      type_="range"
      min="0"
      max="1"
      value={Js.Float.toString(overshoot)}
      step=0.1
      onChange={key_event => {
        let newinput = key_event->ReactEvent.Form.target##value;
        changeOvershoot(_ => float_of_string(newinput));
      }}
    />
    <button
      onClick={_ =>
        changeStages(((_, stage)) =>
          switch (stage) {
          | Before => (Before, After)
          | After => (After, Before)
          }
        )
      }>
      {(
         switch (stage) {
         | Before => "Go"
         | After => "Reset"
         }
       )
       |> React.string}
    </button>
    <BallOvershoot duration overshoot prevStage stage />
  </>;
};
[@react.component]
let make = () => {
  let (duration, changeDuration) = React.useState(() => 1.5);
  let (damping, changeDamping) = React.useState(() => 1.);
  let ((prevStage, stage), changeStages) = React.useState(() => (Ball.Before, Ball.Before));

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
    <h2> {React.string("damping")} </h2>
    <input
      type_="number"
      value={Js.Float.toString(damping)}
      onChange={key_event => {
        let newinput = key_event->ReactEvent.Form.target##value;
        changeDamping(_ => float_of_string(newinput));
      }}
    />
    <input
      type_="range"
      min="0"
      max="1"
      value={Js.Float.toString(damping)}
      step=0.1
      onChange={key_event => {
        let newinput = key_event->ReactEvent.Form.target##value;
        changeDamping(_ => float_of_string(newinput));
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
    <Ball duration damping prevStage stage />
  </>;
};
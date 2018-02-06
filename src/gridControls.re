let component = ReasonReact.statelessComponent("GridControls");

let make =
    (
      ~isAutoplaying,
      ~onReset,
      ~onRandom,
      ~onTick,
      ~onToggleAutoplay,
      _children
    ) => {
  ...component,
  render: _self =>
    <div className="grid-controls">
      <div className="btn-group" role="group">
        <button className="btn btn-danger" onClick=onReset>
          (Utils.text("RESET"))
        </button>
        <button className="btn btn-success" onClick=onRandom>
          (Utils.text("RANDOMIZE"))
        </button>
        <button className="btn btn-secondary" onClick=onTick>
          <i className="mr-2 fa fa-fast-forward" />
          (Utils.text("NEXT"))
        </button>
        <ToggleButton
          label="AUTOPLAY"
          isToggled=isAutoplaying
          onClick=onToggleAutoplay
        />
      </div>
    </div>
};
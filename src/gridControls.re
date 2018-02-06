let component = ReasonReact.statelessComponent("GridControls");

let make =
    (
      ~isPlaying,
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
          (Utils.render_string("RESET"))
        </button>
        <button className="btn btn-success" onClick=onRandom>
          (Utils.render_string("RANDOMIZE"))
        </button>
        <button className="btn btn-secondary" onClick=onTick>
          <i className="mr-2 fa fa-fast-forward" />
          (Utils.render_string("NEXT"))
        </button>
        <ToggleButton
          label="AUTOPLAY"
          isToggled=isPlaying
          onClick=onToggleAutoplay
        />
      </div>
    </div>
};

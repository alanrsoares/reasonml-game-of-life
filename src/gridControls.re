let component = ReasonReact.statelessComponent("GridControls");

let make = (~onReset, ~onRandom, ~onTick, _children) => {
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
        <button className="btn btn-default" onClick=onTick>
          <i
            className="fa fa-fast-forward"
            style=(Utils.style(~marginRight="5px", ()))
          />
          (Utils.text("NEXT"))
        </button>
      </div>
    </div>
};
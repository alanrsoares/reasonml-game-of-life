let component = ReasonReact.statelessComponent("GridControls");

let make = (~onReset, ~onRandom, ~onTick, _children) => {
  ...component,
  render: _self =>
    <div className="grid-controls">
      <div className="btn-group" role="group">
        <button className="btn btn-danger" onClick=onReset>
          (Utils.string("RESET"))
        </button>
        <button className="btn btn-success" onClick=onRandom>
          (Utils.string("RANDOMIZE"))
        </button>
        <button className="btn btn-default" onClick=onTick>
          <i
            className="fa fa-fast-forward"
            style=(Utils.style(~marginRight="5px", ()))
          />
          (Utils.string("NEXT"))
        </button>
      </div>
    </div>
};
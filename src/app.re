let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <div /* GridControls */ />
      <div /* Grid */ />
      <div> <ForkMeOnGithubRibbon /> </div>
    </div>
};
let component = ReasonReact.statelessComponent("ForkMeOnGithubRibbon");

let project_url = "https://github.com/alanrsoares/reasonml-game-of-life";

let ribbon =
  <div className="github-fork-ribbon">
    <a href=project_url> (Utils.string("Fork me on Github")) </a>
  </div>;

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <div className="github-fork-ribbon-wrapper right-bottom visible-xs">
        ribbon
      </div>
      <div className="github-fork-ribbon-wrapper right hidden-xs">
        ribbon
      </div>
    </div>
};
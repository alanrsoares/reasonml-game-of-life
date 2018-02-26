let component = ReasonReact.statelessComponent("GithubForkRibbon");

let project_url = "https://github.com/alanrsoares/reasonml-game-of-life";

let renderRibbon = extraClasses => 
  <div className=("github-fork-ribbon-wrapper " ++ extraClasses)>
    <div className="github-fork-ribbon">
      <a href=project_url> (Utils.render_string("Fork me on Github")) </a>
    </div>
  </div>;

let make = _children => {
  ...component,
  render: _self =>
    <div>
      (renderRibbon("right d-none d-md-block"))
      (renderRibbon("right-bottom d-block d-md-none"))
    </div>
};

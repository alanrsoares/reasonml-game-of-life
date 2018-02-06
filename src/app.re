type state = {
  grid: Game.grid,
  isAutoplaying: bool,
  animationFrameId: ref(int)
};

type action =
  | Random
  | Reset
  | Start
  | Stop
  | Tick
  | Toggle(Game.position);

let get_seed = () => int_of_float(Js.Date.now());

let component = ReasonReact.reducerComponent("App");

let make = (~boardSize=30, _children) => {
  ...component,
  initialState: () => {
    grid: Game.make_random_grid(boardSize, get_seed()),
    isAutoplaying: false,
    animationFrameId: ref(0)
  },
  reducer: (action, state) =>
    switch action {
    | Random =>
      ReasonReact.Update({
        ...state,
        grid: Game.make_random_grid(boardSize, get_seed())
      })
    | Reset => ReasonReact.Update({...state, grid: Game.make_blank_grid(30)})
    | Start => ReasonReact.Update({...state, isAutoplaying: true})
    | Stop => ReasonReact.Update({...state, isAutoplaying: false})
    | Tick =>
      ReasonReact.Update({...state, grid: Game.next_generation(state.grid)})
    | Toggle(position) =>
      ReasonReact.Update({
        ...state,
        grid: Game.toggle_tile(position, state.grid)
      })
    },
  render: self =>
    <div>
      <GridControls
        isAutoplaying=self.state.isAutoplaying
        onReset=((_) => self.send(Reset))
        onRandom=((_) => self.send(Random))
        onTick=((_) => self.send(Tick))
        onToggleAutoplay=(
          (_) => {
            let rec autoplay = () => {
              self.state.animationFrameId :=
                Utils.requestAnimationFrame(autoplay);
              self.send(Tick);
            };
            if (self.state.isAutoplaying) {
              Utils.cancelAnimationFrame(self.state.animationFrameId^);
              self.send(Stop);
            } else {
              autoplay();
              self.send(Start);
            };
          }
        )
      />
      <div>
        <Grid
          data=self.state.grid
          onToggle=((y, x) => self.send(Toggle({y, x})))
        />
      </div>
      <ForkMeOnGithubRibbon />
    </div>
};
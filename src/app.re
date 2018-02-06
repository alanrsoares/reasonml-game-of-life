type state = {
  grid: Game.grid,
  isRunning: bool,
  animationFrameId: ref(int)
};

type action =
  | StartAutoplay
  | StopAutoplay
  | Tick
  | Random
  | Reset
  | Toggle(Game.position);

let get_seed = () => int_of_float(Js.Date.now());

let component = ReasonReact.reducerComponent("TodoApp");

let make = _children => {
  ...component,
  initialState: () => {
    grid: Game.make_random_grid(30, get_seed()),
    isRunning: false,
    animationFrameId: ref(0)
  },
  reducer: (action, state) =>
    switch action {
    | StartAutoplay => ReasonReact.Update({...state, isRunning: true})
    | StopAutoplay => ReasonReact.Update({...state, isRunning: false})
    | Random =>
      ReasonReact.Update({
        ...state,
        grid: Game.make_random_grid(30, get_seed())
      })
    | Reset => ReasonReact.Update({...state, grid: Game.make_blank_grid(30)})
    | Tick =>
      ReasonReact.Update({...state, grid: Game.next_generation(state.grid)})
    | Toggle(position) =>
      ReasonReact.Update({...state, grid: Game.toggle(position, state.grid)})
    },
  render: self =>
    <div>
      <GridControls
        isRunning=self.state.isRunning
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
            if (self.state.isRunning) {
              Utils.cancelAnimationFrame(self.state.animationFrameId^);
              self.send(StopAutoplay);
            } else {
              autoplay();
              self.send(StartAutoplay);
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
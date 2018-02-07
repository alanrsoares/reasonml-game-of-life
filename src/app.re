[%bs.raw {|require('./app.css')|}];

type state = {
  grid: Game.grid,
  isPlaying: bool,
  animationFrameId: ref(int),
  score: ref(int)
};

type action =
  | Random
  | Reset
  | Start
  | Stop
  | Tick
  | Toggle(Game.position);

type self_props = ReasonReact.self(state, ReasonReact.noRetainedProps, action);

let make_seed = () => int_of_float(Js.Date.now());

let component = ReasonReact.reducerComponent("App");

let handle_toggle_autoplay = (self: self_props, _) => {
  let rec play = () => {
    self.state.animationFrameId := Utils.request_animation_frame(play);
    self.send(Tick);
  };
  if (self.state.isPlaying) {
    Utils.cancel_animation_frame(self.state.animationFrameId^);
    self.send(Stop);
  } else {
    play();
    self.send(Start);
  };
};

let make = (~tileSize, ~boardSize, _children) => {
  ...component,
  initialState: () => {
    grid: Game.make_random_grid(boardSize, make_seed()),
    isPlaying: false,
    animationFrameId: ref(0),
    score: ref(0)
  },
  reducer: (action, state) =>
    switch action {
    | Random =>
      ReasonReact.Update({
        ...state,
        grid: Game.make_random_grid(boardSize, make_seed()),
        score: ref(0)
      })
    | Reset => ReasonReact.Update({
      ...state,
      grid: Game.make_blank_grid(30),
      score: ref(0)
    })
    | Start => ReasonReact.Update({...state, isPlaying: true})
    | Stop => ReasonReact.Update({...state, isPlaying: false})
    | Tick =>
      ReasonReact.Update({
        ...state,
        grid: Game.next_generation(state.score, state.grid)
      })
    | Toggle(position) =>
      ReasonReact.Update({
        ...state,
        grid: Game.toggle_tile(position, state.grid)
      })
    },
  render: self =>
    <div className="App">
      <GridControls
        isPlaying=self.state.isPlaying
        onReset=((_) => self.send(Reset))
        onRandom=((_) => self.send(Random))
        onTick=((_) => self.send(Tick))
        onToggleAutoplay=(handle_toggle_autoplay(self))
      />
      <div className="App--score align-text-center">
        (Utils.render_string(string_of_int(self.state.score^)))
      </div>
      <Grid
        tileSize
        data=self.state.grid
        onToggle=((y, x) => self.send(Toggle({y, x})))
      />
      <GithubForkRibbon />
    </div>
};

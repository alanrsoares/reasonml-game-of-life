open Jest;
open Expect;

describe("Game", () => {
  let x = Game.Alive;
  let o = Game.Dead;

  describe("make_random_grid", () =>
    test("should create a grid with the correct length", () =>
      expect(Game.make_random_grid(3, 2) |> Array.length) |> toBe(3)
    )
  );

  describe("get_tile", () =>
    test("should get the value of a tile given the positions", () => {
      let grid = [|[|o, o, o|], [|x, x, x|], [|o, o, o|]|];
      let tile_position = (1, 1);

      expect(grid->Game.get_tile(tile_position)) |> toBe(Game.Alive);
    })
  );

  describe("count_living_neighbours", () =>
    test("should get number of live neighbours of a given tile", () => {
      let grid = [|[|o, o, o|], [|x, x, x|], [|o, o, o|]|];
      let tile_position = (0, 1);

      expect(grid->Game.count_living_neighbours(tile_position)) |> toBe(3);
    })
  );

  describe("toggle_cell", () => {
    let grid = [|[|o, o, o|], [|x, x, x|], [|o, o, o|]|];
    let next_grid = [|[|o, o, o|], [|x, o, x|], [|o, o, o|]|];
    let tile_position = (1, 1);

    test("should toggle the middle cell", () =>
      expect(grid->Game.toggle_tile(tile_position)) |> toEqual(next_grid)
    );

    test("should revert the middle cell to its original state", () =>
      expect(next_grid->Game.toggle_tile(tile_position)) |> toEqual(grid)
    );
  });

  describe("next_generation", () => {
    describe("the cross pattern", () => {
      let grid = [|
        [|o, o, o, o, o|],
        [|o, o, o, o, o|],
        [|o, x, x, x, o|],
        [|o, o, o, o, o|],
        [|o, o, o, o, o|],
      |];
      let next_grid = [|
        [|o, o, o, o, o|],
        [|o, o, x, o, o|],
        [|o, o, x, o, o|],
        [|o, o, x, o, o|],
        [|o, o, o, o, o|],
      |];

      test("should transform a horizontal to a vertical line", () =>
        expect(grid |> Game.next_generation(ref(0))) |> toEqual(next_grid)
      );

      test("should revert a vertical line to a horizontal one", () =>
        expect(next_grid |> Game.next_generation(ref(0))) |> toEqual(grid)
      );
    });

    describe("the glider pattern", () => {
      let grid = [|
        [|o, x, o, o, o|],
        [|o, o, x, o, o|],
        [|x, x, x, o, o|],
        [|o, o, o, o, o|],
        [|o, o, o, o, o|],
      |];
      let next_grid = [|
        [|o, o, o, o, o|],
        [|x, o, x, o, o|],
        [|o, x, x, o, o|],
        [|o, x, o, o, o|],
        [|o, o, o, o, o|],
      |];

      test("should move a glider to the next step", () =>
        expect(grid |> Game.next_generation(ref(0))) |> toEqual(next_grid)
      );
    });
  });
});
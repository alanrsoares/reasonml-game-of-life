open Jest;

open Expect;

describe("Game", (_) => {
  let x = true;
  let o = false;
  describe("make_grid", (_) =>
    test("should create a grid with the correct length", (_) =>
      expect(Game.make_grid(3) |> List.length) |> toBe(3)
    )
  );
  describe("get_tile", (_) =>
    test("should get the value of a tile given the positions", (_) => {
      let grid = [[o, o, o], [x, x, x], [o, o, o]];
      let tile_position: Game.position = {y: 1, x: 1};
      expect(grid |> Game.get_tile(tile_position)) |> toBe(true);
    })
  );
  describe("count_living_neighbours", (_) =>
    test("should get number of live neighbours of a given tile", (_) => {
      let grid = [[o, o, o], [x, x, x], [o, o, o]];
      let tile_position: Game.position = {y: 0, x: 1};
      expect(grid |> Game.count_living_neighbours(tile_position)) |> toBe(3);
    })
  );
  describe("next_generation", (_) => {
    describe("the cross pattern", (_) => {
      let grid = [
        [o, o, o, o, o],
        [o, o, o, o, o],
        [o, x, x, x, o],
        [o, o, o, o, o],
        [o, o, o, o, o]
      ];
      let next_grid = [
        [o, o, o, o, o],
        [o, o, x, o, o],
        [o, o, x, o, o],
        [o, o, x, o, o],
        [o, o, o, o, o]
      ];
      test("should transform a horizontal to a vertical line", (_) =>
        expect(grid |> Game.next_generation) |> toEqual(next_grid)
      );
      test("should revert a vertical line to a horizontal one", (_) =>
        expect(next_grid |> Game.next_generation) |> toEqual(grid)
      );
    });
    describe("the glider pattern", (_) => {
      let grid = [
        [o, x, o, o, o],
        [o, o, x, o, o],
        [x, x, x, o, o],
        [o, o, o, o, o],
        [o, o, o, o, o]
      ];
      let next_grid = [
        [o, o, o, o, o],
        [x, o, x, o, o],
        [o, x, x, o, o],
        [o, x, o, o, o],
        [o, o, o, o, o]
      ];
      test("should move a glider to the next step", (_) =>
        expect(grid |> Game.next_generation) |> toEqual(next_grid)
      );
    });
  });
});
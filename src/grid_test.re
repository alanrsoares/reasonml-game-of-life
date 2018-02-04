open Jest;
open Expect;

describe("Grid", (_) => {
  let x = true;

  let o = false;

  describe("make", (_) =>
    test("should create a grid with the correct length", (_) =>
      expect(Grid.make(3) |> List.length) |> toBe(3)
    )
  );
  describe("get", (_) =>
    test("should get the value of a cell given the positions", (_) => {
      let grid = [[o, o, o], [x, x, x], [o, o, o]];
      let cell_position: Grid.position = {y: 1, x: 1};
      expect(grid |> Grid.get(cell_position)) |> toBe(true);
    })
  );
  describe("count_living_neighbours", (_) =>
    test("should get number of live neighbours of a given cell", (_) => {
      let grid = [[o, o, o], [x, x, x], [o, o, o]];
      let cell_position: Grid.position = {y: 0, x: 1};
      expect(grid |> Grid.count_living_neighbours(cell_position)) |> toBe(3);
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
        expect(grid |> Grid.next_generation) |> toEqual(next_grid)
      );
      test("should revert a vertical line to a horizontal one", (_) =>
        expect(next_grid |> Grid.next_generation) |> toEqual(grid)
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
        expect(grid |> Grid.next_generation) |> toEqual(next_grid)
      );
    });
  });
});
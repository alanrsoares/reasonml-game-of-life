open Jest;

open Expect;

let t = true;

let f = false;

describe("Grid", (_) => {
  describe("make", (_) =>
    test("should create a grid with the correct length", (_) =>
      expect(Grid.make(3) |> List.length) |> toBe(3)
    )
  );
  describe("get", (_) =>
    test("should get the value of a cell given the positions", (_) => {
      let grid = [[f, f, f], [t, t, t], [f, f, f]];
      let cell_position: Grid.position = {y: 1, x: 1};
      expect(grid |> Grid.get(cell_position)) |> toBe(t);
    })
  );
  describe("count_living_neighbours", (_) =>
    test("should get number of live neighbours of a given cell", (_) => {
      let grid = [[f, f, f], [t, t, t], [f, f, f]];
      let cell_position: Grid.position = {y: 0, x: 1};
      expect(grid |> Grid.count_living_neighbours(cell_position)) |> toBe(3);
    })
  );
  describe("next_generation", (_) => {
    describe("the cross pattern", (_) => {
      let grid = [
        [f, f, f, f, f],
        [f, f, f, f, f],
        [f, t, t, t, f],
        [f, f, f, f, f],
        [f, f, f, f, f]
      ];
      let next_grid = [
        [f, f, f, f, f],
        [f, f, t, f, f],
        [f, f, t, f, f],
        [f, f, t, f, f],
        [f, f, f, f, f]
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
        [f, t, f, f, f],
        [f, f, t, f, f],
        [t, t, t, f, f],
        [f, f, f, f, f],
        [f, f, f, f, f]
      ];
      let next_grid = [
        [f, f, f, f, f],
        [t, f, t, f, f],
        [f, t, t, f, f],
        [f, t, f, f, f],
        [f, f, f, f, f]
      ];
      test("should move a glider to the next step", (_) =>
        expect(grid |> Grid.next_generation) |> toEqual(next_grid)
      );
    });
  });
});
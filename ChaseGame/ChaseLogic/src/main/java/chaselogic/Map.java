package chaselogic;

import java.util.Arrays;

public class Map {
    private final Entity[][] grid;

    public Map(int height, int width) {
        grid = new Entity[height][width];
        initializeGrid();
    }

    private void initializeGrid() {
        for (Entity[] entities : grid) {
            Arrays.fill(entities, Entity.EMPTY);
        }
    }

    public Entity getObjectAt(int x, int y) {
        return grid[x][y];
    }

    public void setObjectAt(int x, int y, Entity object) {
        grid[x][y] = object;
    }

    public int getHeight() {
        return grid.length;
    }

    public int getWidth() {
        return grid[0].length;
    }

    public Entity[][] getGrid() {
        return grid;
    }
}
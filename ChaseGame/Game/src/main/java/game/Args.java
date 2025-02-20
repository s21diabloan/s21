package game;

import com.beust.jcommander.Parameter;
import com.beust.jcommander.Parameters;

@Parameters(separators = "=")
public class Args {
    @Parameter(names = "--enemiesCount", required = true,
            description = "Number of enemies in the game")
    private int enemiesCount;

    @Parameter(names = "--wallsCount", required = true,
            description = "Number of walls in the game")
    private int wallsCount;

    @Parameter(names = "--size", required = true,
            description = "Size of the game map")
    private int size;

    @Parameter(names = "--profile", required = true,
            description = "Profile for the game configuration (e.g., dev, prod)")
    private String profile;

    public Args() {
    }

    public int getEnemiesCount() {
        return enemiesCount;
    }

    public int getWallsCount() {
        return wallsCount;
    }

    public int getSize() {
        return size;
    }

    public String getProfile() {
        return profile;
    }

    @Override
    public String toString() {
        return "--enemiesCount=" + enemiesCount + " --wallsCount=" + wallsCount +
                " --size=" + size + " --profile=" + profile;
    }
}
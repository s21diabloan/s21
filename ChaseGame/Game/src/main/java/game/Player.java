package game;

public class Player {
    private final int[] coordinates;

    public Player() {
        coordinates = new int[2];
    }

    public int[] getCoordinates() {
        return new int[]{coordinates[0], coordinates[1]};
    }

    public void setCoordinates(int x, int y) {
        coordinates[0] = x;
        coordinates[1] = y;
    }
}
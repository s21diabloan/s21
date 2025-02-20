package chaselogic;

public class Enemy {

    private final int[] coordinates;

    public Enemy() {
        coordinates = new int[2];
    }

    public int[] getCoordinates() {
        return coordinates;
    }


    public void setCoordinates(int x, int y) {
        coordinates[0] = x;
        coordinates[1] = y;
    }
}
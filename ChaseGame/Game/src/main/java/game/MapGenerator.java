package game;

import chaselogic.Enemy;
import chaselogic.Entity;
import chaselogic.Map;

public class MapGenerator {
    private static Data data;
    private static int width;
    private static int height;

    public MapGenerator(Data data) {
        MapGenerator.data = data;
        width = data.getWeight();
        height = data.getHeight();
    }

    public Map generateMap() {
        Map map = new Map(height, width);

        for (int i = 0; i < data.getEnemiesCount(); i++) {
            int[] randomCoordinates = generateUniqueCoordinates(map);
            addEnemy(data, randomCoordinates[0], randomCoordinates[1]);
            map.setObjectAt(randomCoordinates[0], randomCoordinates[1], Entity.ENEMY);
        }

        for (int i = 0; i < data.getWallsCount(); i++) {
            int[] randomCoordinates = generateUniqueCoordinates(map);
            map.setObjectAt(randomCoordinates[0], randomCoordinates[1], Entity.WALLS);
        }
        int[] playerCoordinates = generateUniqueCoordinates(map);
        map.setObjectAt(playerCoordinates[0], playerCoordinates[1], Entity.PLAYER);
        data.setPlayerCoordinates(playerCoordinates[0], playerCoordinates[1]);

        int[] pointCoordinates = generateUniqueCoordinates(map);
        map.setObjectAt(pointCoordinates[0], pointCoordinates[1], Entity.POINT);

        return map;
    }

    private static void addEnemy(Data data, int x, int y) {
        Enemy enemy = new Enemy();
        enemy.setCoordinates(x, y);
        data.setEnemies(enemy);
    }

    private static int[] generateUniqueCoordinates(Map map) {
        int x, y;
        do {
            x = (int) (Math.random() * height);
            y = (int) (Math.random() * width);
        } while (map.getObjectAt(x, y) != Entity.EMPTY);
        return new int[]{x, y};
    }
}

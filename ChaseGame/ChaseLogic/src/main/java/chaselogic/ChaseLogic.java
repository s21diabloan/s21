package chaselogic;

import java.util.List;

public class ChaseLogic {
    private final Map map;
    private final EnemyMovement enemyMovement;
    private boolean isChased = false;
    private int[] playerCoordinates;

    public ChaseLogic(Map map) {
        this.map = map;
        enemyMovement = new EnemyMovement(map, this);
    }

    public void invokeEnemies(List<Enemy> enemies, int[] playerCoordinates) {
        this.playerCoordinates = playerCoordinates;
        int playerX = playerCoordinates[0];
        int playerY = playerCoordinates[1];
        for (Enemy enemy : enemies) {
            int enemyX = enemy.getCoordinates()[0];
            int enemyY = enemy.getCoordinates()[1];
            moveValidation(playerX, playerY, enemy, enemyX, enemyY);
        }
    }

    private void moveValidation(int playerX, int playerY, Enemy enemy, int enemyX, int enemyY) {
        int difX = playerX - enemyX;
        int difY = playerY - enemyY;

        if (Math.abs(difX) > Math.abs(difY)) {
            if (difX > 0 && isValidMove(enemyX + 1, enemyY)) {
                enemyMovement.moveBack(enemy);
            } else if (difX < 0 && isValidMove(enemyX - 1, enemyY)) {
                enemyMovement.moveForward(enemy);
            }
        } else {
            if (difY > 0 && isValidMove(enemyX, enemyY + 1)) {
                enemyMovement.moveRight(enemy);
            } else if (difY < 0 && isValidMove(enemyX, enemyY - 1)) {
                enemyMovement.moveLeft(enemy);
            }
        }
    }

    private boolean isValidMove(int x, int y) {
        return chekValidMove(x, y, map);
    }

    static boolean chekValidMove(int x, int y, Map map) {
        return x >= 0 && x < map.getHeight() && y >= 0 && y < map.getWidth() && map.getObjectAt(x, y) != Entity.WALLS && map.getObjectAt(x, y) != Entity.POINT && map.getObjectAt(x, y) != Entity.ENEMY;
    }

    public void updateEnemyCoordinates(Map map, int x, int y, Entity object, Enemy enemy) {
        map.setObjectAt(x, y, object);
        enemy.setCoordinates(x, y);
    }

    public void caught(int x, int y) {
        if (x == playerCoordinates[0] && y == playerCoordinates[1]) {
            isChased = true;
        }
    }

    public int[] getPlayerCoordinates() {
        return playerCoordinates;
    }

    public boolean isChased() {
        return isChased;
    }
}
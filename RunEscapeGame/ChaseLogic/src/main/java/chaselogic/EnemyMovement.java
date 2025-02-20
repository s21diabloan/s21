package chaselogic;

public class EnemyMovement {
    private final Map map;
    private final ChaseLogic chaseLogic;

    public EnemyMovement(Map map, ChaseLogic chaseLogic) {
        this.map = map;
        this.chaseLogic = chaseLogic;
    }

    public void moveEnemy(Enemy enemy, int newX, int newY) {
        int x = enemy.getCoordinates()[0];
        int y = enemy.getCoordinates()[1];

        if (isValidMove(newX, newY)) {
            if (newX == chaseLogic.getPlayerCoordinates()[0] && newY == chaseLogic.getPlayerCoordinates()[1]) {
                chaseLogic.caught(newX, newY);
                map.setObjectAt(x, y, Entity.EMPTY);
                map.setObjectAt(newX, newY, Entity.ENEMY);
                enemy.setCoordinates(newX, newY);
                return;
            }
            map.setObjectAt(x, y, Entity.EMPTY);
            chaseLogic.updateEnemyCoordinates(map, newX, newY, Entity.ENEMY, enemy);
        } else {
            chaseLogic.updateEnemyCoordinates(map, x, y, Entity.ENEMY, enemy);
        }
    }

    public void moveForward(Enemy enemy) {
        int x = enemy.getCoordinates()[0];
        moveEnemy(enemy, x - 1, enemy.getCoordinates()[1]);
    }

    public void moveBack(Enemy enemy) {
        int x = enemy.getCoordinates()[0];
        moveEnemy(enemy, x + 1, enemy.getCoordinates()[1]);
    }

    public void moveLeft(Enemy enemy) {
        int y = enemy.getCoordinates()[1];
        moveEnemy(enemy, enemy.getCoordinates()[0], y - 1);
    }

    public void moveRight(Enemy enemy) {
        int y = enemy.getCoordinates()[1];
        moveEnemy(enemy, enemy.getCoordinates()[0], y + 1);
    }

    private boolean isValidMove(int x, int y) {
        return ChaseLogic.chekValidMove(x, y, map);
    }
}
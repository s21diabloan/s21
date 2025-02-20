package game;

import chaselogic.Entity;
import chaselogic.Map;

import java.io.FileNotFoundException;
import java.util.Scanner;

public class PlayerMovement {
    private final Data data;
    private final Game gameManager;
    Scanner scanner = new Scanner(System.in);

    public PlayerMovement(Data data, Game gameManager) {
        this.data = data;
        this.gameManager = gameManager;
    }

    public void moveForward(Map map) throws FileNotFoundException {
        int x = data.getPlayerCoordinates()[0];
        int y = data.getPlayerCoordinates()[1];

        if (x == 0 || map.getObjectAt(x - 1, y) == Entity.WALLS) {
            System.out.println("You cannot move beyond the top border!");
            System.out.print("Enter a new direction (A, S, or D): ");
            String command = scanner.nextLine().trim().toLowerCase();
            switch (command) {
                case "a":
                    moveLeft(map);
                    break;
                case "s":
                    moveBack(map);
                    break;
                case "d":
                    moveRight(map);
                    break;
                default:
                    System.out.println("Invalid direction!");
                    break;
            }
            return;
        } else {
            Entity nextEntity = map.getObjectAt(x - 1, y);
            if (nextEntity == Entity.ENEMY) {
                System.out.println("You were caught by an enemy!");
                gameManager.promptForRetry();
                return;
            } else {
                map.setObjectAt(x, y, Entity.EMPTY);
                x -= 1;
            }
        }
        gameManager.checkGameStatus(map, x, y);
    }

    public void moveBack(Map map) throws FileNotFoundException {
        int x = data.getPlayerCoordinates()[0];
        int y = data.getPlayerCoordinates()[1];

        if (x == data.getHeight() - 1 || map.getObjectAt(x + 1, y) == Entity.WALLS) {
            System.out.println("You cannot move beyond the bottom border!");
            System.out.print("Enter a new direction (A, W, or D): ");
            String command = scanner.nextLine().trim().toLowerCase();
            switch (command) {
                case "a":
                    moveLeft(map);
                    break;
                case "w":
                    moveForward(map);
                    break;
                case "d":
                    moveRight(map);
                    break;
                default:
                    System.out.println("Invalid direction!");
                    break;
            }
            return;
        } else {
            Entity nextEntity = map.getObjectAt(x + 1, y);
            if (nextEntity == Entity.ENEMY) {
                System.out.println("You were caught by an enemy!");
                gameManager.promptForRetry();
                return;
            } else {
                map.setObjectAt(x, y, Entity.EMPTY);
                x += 1;
            }
        }
        gameManager.checkGameStatus(map, x, y);
    }

    public void moveLeft(Map map) throws FileNotFoundException {
        int x = data.getPlayerCoordinates()[0];
        int y = data.getPlayerCoordinates()[1];

        if (y == 0 || map.getObjectAt(x, y - 1) == Entity.WALLS) {
            newDirection(map);
            return;
        } else {
            Entity nextEntity = map.getObjectAt(x, y - 1);
            if (nextEntity == Entity.ENEMY) {
                System.out.println("You were caught by an enemy!");
                gameManager.promptForRetry();
                return;
            } else {
                map.setObjectAt(x, y, Entity.EMPTY);
                y -= 1;
            }
        }
        gameManager.checkGameStatus(map, x, y);
    }

    private void newDirection(Map map) throws FileNotFoundException {
        System.out.println("You cannot move beyond the left border!");
        System.out.print("Enter a new direction (W, S, or D): ");
        String command = scanner.nextLine().trim().toLowerCase();
        switch (command) {
            case "w":
                moveForward(map);
                break;
            case "s":
                moveBack(map);
                break;
            case "d":
                moveRight(map);
                break;
            default:
                System.out.println("Invalid direction!");
                break;
        }
    }

    public void moveRight(Map map) throws FileNotFoundException {
        int x = data.getPlayerCoordinates()[0];
        int y = data.getPlayerCoordinates()[1];

        if (y == data.getWeight() - 1 || map.getObjectAt(x, y + 1) == Entity.WALLS) {
            System.out.println("You cannot move beyond the right border!");
            System.out.print("Enter a new direction (W, A, or S): ");
            String command = scanner.nextLine().trim().toLowerCase();
            switch (command) {
                case "w":
                    moveForward(map);
                    break;
                case "a":
                    moveLeft(map);
                    break;
                case "s":
                    moveBack(map);
                    break;
                default:
                    System.out.println("Invalid direction!");
                    break;
            }
        } else {
            Entity nextEntity = map.getObjectAt(x, y + 1);
            if (nextEntity == Entity.ENEMY) {
                System.out.println("You were caught by an enemy!");
                gameManager.promptForRetry();
                return;
            } else {
                map.setObjectAt(x, y, Entity.EMPTY);
                y += 1;
            }
            gameManager.checkGameStatus(map, x, y);
        }
    }
}

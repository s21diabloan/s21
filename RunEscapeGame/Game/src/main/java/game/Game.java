package game;

import chaselogic.ChaseLogic;
import chaselogic.Entity;
import chaselogic.Map;

import java.io.FileNotFoundException;
import java.nio.file.Path;
import java.util.Scanner;

public class Game {
    private static Scanner scanner;
    private Data data;
    private PlayerMovement playerMovement;
    private MapPainter mapPainter;
    private ChaseLogic chaseLogic;
    private Map map;
    private final Path pathProperties;
    private final Args jargs;
    private static boolean isRendered = false;
    private static boolean isDev = false;

    public Game(Path pathProperties, Args jargs) {
        this.pathProperties = pathProperties;
        this.jargs = jargs;
        scanner = new Scanner(System.in);
    }

    public void startGame() throws FileNotFoundException {
        if (!isRendered) {
            mapRendering();
            isRendered = true;
        }
        mapPainter.paintMap(map);

        while (true) {
            System.out.print("Move->");
            String command = scanner.nextLine();

            if (command.equals("9")) {
                System.out.println("Exit");
                System.exit(0);
            }

            switch (command.toLowerCase()) {
                case "w":
                    playerMovement.moveForward(map);
                    break;
                case "s":
                    playerMovement.moveBack(map);
                    break;
                case "a":
                    playerMovement.moveLeft(map);
                    break;
                case "d":
                    playerMovement.moveRight(map);
                    break;
                default:
                    System.out.println("Enter W, A, S, or D.");
            }
        }
    }

    private void mapRendering() {
        data = new Data(ParseProperties.parserHandler(pathProperties), jargs);
        isDev = data.getProfile().equals("dev");
        mapPainter = new MapPainter(data);
        playerMovement = new PlayerMovement(data, this);
        MapGenerator mapGenerator = new MapGenerator(data);
        map = mapGenerator.generateMap();
        chaseLogic = new ChaseLogic(map);
    }
    

    public void checkGameStatus(Map map, int x, int y) throws FileNotFoundException {

        if (Entity.POINT.equals(map.getObjectAt(x, y))) {
            System.out.println("You won!");
            promptForRetry();
        } else {
            updateMap(x, y, Entity.PLAYER);
        }

        // Проверка статуса логики преследования
        if (chaseLogic.isChased()) {
            System.out.println("You was chased!");
            promptForRetry();
        }
    }

    void promptForRetry() throws FileNotFoundException {
        while (true) {
            System.out.print("Retry? Yes/No -> ");
            String command = scanner.nextLine().trim().toLowerCase();

            if (command.equals("yes") || command.equals("y")) {
                isRendered = false;
                startGame();
                break;
            } else if (command.equals("no") || command.equals("n")) {
                System.exit(0);
            } else {
                System.out.println("Retry? Yes/No ->");
            }
        }
    }

    private void updateMap(int x, int y, Entity object) throws FileNotFoundException {
        map.setObjectAt(x, y, object);
        data.setPlayerCoordinates(x, y);
        mapPainter.paintMap(map);
        if (isDev) {
            handleDevMode(x, y, object);
        } else {
            chaseLogic.invokeEnemies(data.getEnemies(), data.getPlayerCoordinates());
            mapPainter.paintMap(map);
        }
    }

    private void handleDevMode(int x, int y, Entity object) throws FileNotFoundException {
        System.out.print("Enter 8 to accept enemy step or 9 to exit -> ");
        String command = scanner.nextLine();

        switch (command) {
            case "8":
                chaseLogic.invokeEnemies(data.getEnemies(), data.getPlayerCoordinates());
                mapPainter.paintMap(map);
                break;
            case "9":
                System.exit(0);
                break;
            default:
                updateMap(x, y, object);
        }
    }
}
package game;

import chaselogic.Entity;
import com.diogonunes.jcdp.color.ColoredPrinter;
import com.diogonunes.jcdp.color.api.Ansi;

public class MapPainter {
    private final Data data;

    public MapPainter(Data data) {
        this.data = data;
    }

    public void paintMap(chaselogic.Map map) {
        if (!data.isDev()) {
            System.out.print("\033[H\033[2J");
            System.out.flush();
        }

        int weight = data.getWeight();
        int height = data.getHeight();
        ColoredPrinter cp = new ColoredPrinter.Builder(1, false).background(Ansi.BColor.WHITE).build();

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < weight; j++) {
                Entity entity = map.getObjectAt(i, j);

                if (entity.equals(Entity.PLAYER)) {
                    cp.print(data.getPlayerChar(), Ansi.Attribute.NONE, Ansi.FColor.NONE, Ansi.BColor.valueOf(data.getPlayerColor()));
                } else if (entity.equals(Entity.ENEMY)) {
                    cp.print(data.getEnemyChar(), Ansi.Attribute.NONE, Ansi.FColor.NONE, Ansi.BColor.valueOf(data.getEnemyColor()));
                } else if (entity.equals(Entity.WALLS)) {
                    cp.print(data.getWallChar(), Ansi.Attribute.NONE, Ansi.FColor.NONE, Ansi.BColor.valueOf(data.getWallColor()));
                } else if (entity.equals(Entity.POINT)) {
                    cp.print(data.getGoalChar(), Ansi.Attribute.NONE, Ansi.FColor.NONE, Ansi.BColor.valueOf(data.getGoalColor()));
                } else {
                    cp.print(data.getEmptyChar(), Ansi.Attribute.NONE, Ansi.FColor.NONE, Ansi.BColor.valueOf(data.getEmptyColor()));
                }
            }
            System.out.println();
        }
    }
}
package chaselogic;

public class Entity {
    private final int value;

    public static final Entity ENEMY = new Entity(1);
    public static final Entity PLAYER = new Entity(2);
    public static final Entity WALLS = new Entity(3);
    public static final Entity POINT = new Entity(4);
    public static final Entity EMPTY = new Entity(0);

    private Entity(int value) {
        this.value = value;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Entity that = (Entity) obj;
        return value == that.value;
    }
}
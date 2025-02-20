package game;

public class IllegalParametersException extends RuntimeException {
    public IllegalParametersException(String message) {
        super(message);
    }
}
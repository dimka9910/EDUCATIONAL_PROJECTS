package course.entity;

import org.springframework.security.core.GrantedAuthority;

public enum Role1 implements GrantedAuthority {
    USER, ADMIN, BUSY;

    @Override
    public String getAuthority() {
        return name();
    }
}

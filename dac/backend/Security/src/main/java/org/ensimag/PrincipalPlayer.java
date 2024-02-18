package org.ensimag;

import java.util.ArrayList;
import java.util.Collection;

import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;

// Class to implements methods used by security to retrieve Players from the database
public class PrincipalPlayer implements UserDetails, GrantedAuthority {
    private Playerdto player;

    public PrincipalPlayer(Playerdto player) {
        this.player = player;
    }

    @Override
    public Collection<PrincipalPlayer> getAuthorities() {
        ArrayList<PrincipalPlayer> res = new ArrayList<>();
        res.add(this);
        return res;
    }

    @Override
    public String getPassword() {
        return player.getPassword();
    }

    @Override
    public String getUsername() {
        return player.getSurname();
    }

    @Override
    public boolean isAccountNonExpired() {
        return true;
    }

    @Override
    public boolean isAccountNonLocked() {
        return true;
    }

    @Override
    public boolean isCredentialsNonExpired() {
        return true;
    }

    @Override
    public boolean isEnabled() {
        return true;
    }

    @Override
    public String getAuthority() {
        return "Player";
    }
}

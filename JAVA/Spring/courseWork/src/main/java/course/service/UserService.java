package course.service;

import course.entity.Role1;
import course.entity.User;
import course.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.IncorrectResultSizeDataAccessException;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import java.util.Collections;
import java.util.List;

@Service
public class UserService implements UserDetailsService {
    @PersistenceContext
    private EntityManager em;
    @Autowired
    UserRepository userRepository;

    @Autowired
    BCryptPasswordEncoder bCryptPasswordEncoder;

    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        try {
            User user = userRepository.findByUsername(username);

            if (user == null) {
                throw new UsernameNotFoundException("User not found");
            }

            return user;

        } catch (IncorrectResultSizeDataAccessException ex) {
            System.out.println("USER EXISTS IN DUPLICATE!");
            return null;
        }
    }

    public User getUserById(Long userId) {
        return userRepository.findById(userId).orElse(null);
    }

    public List<User> getAllUsers() {
        return userRepository.findAll();
    }

    public void addUser(User user) {
        try {
            if (userRepository.findByUsername(user.getUsername()) != null) {
                throw new UnsupportedOperationException("user already exists");
            } else {
                //user.setRoles(Collections.singleton(new Role(1L, "USER")));
                //НАДО ВЕРНУТЬСЯ!!
                user.setRoles(Collections.singleton(Role1.USER));
                user.setPassword(user.getPassword());
                userRepository.save(user);
            }
        } catch (IncorrectResultSizeDataAccessException ex) {
            System.out.println("USER EXISTS IN DUPLICATE!");
        }
    }

    public void deleteUser(Long userId) {
        if (userRepository.findById(userId).isPresent()) {
            userRepository.deleteById(userId);
        } else {
            throw new IllegalArgumentException("user does not exist");
        }
    }
}

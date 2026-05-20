package org.example.skelet.repository;

import org.example.skelet.domain.entities.Admin;
import org.example.skelet.domain.entities.Cashier;
import org.example.skelet.domain.entities.User;
import org.example.skelet.repository.exceptions.RepositoryException;

import java.sql.*;
import java.util.Optional;

public class UserDBRepository extends DatabaseRepository<Long, User> implements UserRepository {
    public UserDBRepository(String url, String username, String password) {
        super(url, username, password);
    }
    @Override
    public PreparedStatement findOneStatement(Connection connection, Long aLong) throws SQLException {
        PreparedStatement ps = connection.prepareStatement("SELECT * FROM users WHERE id = ?");
        ps.setLong(1, aLong);
        return ps;
    }

    @Override
    public PreparedStatement findAllStatement(Connection connection) throws SQLException {
        PreparedStatement ps = connection.prepareStatement("SELECT * FROM users");
        return ps;
    }

    @Override
    public PreparedStatement saveStatement(Connection connection, User entity) throws SQLException {
        PreparedStatement ps = connection.prepareStatement("INSERT INTO users (id, username,password, type) VALUES (?, ?, ?, ?)");
        ps.setLong(1, entity.getId());
        ps.setString(2, entity.getName());
        ps.setString(3, entity.getPassword());
        ps.setString(4, entity.getType());
        return ps;
    }

    @Override
    public PreparedStatement deleteStatement(Connection connection, Long aLong) throws SQLException {
        PreparedStatement ps = connection.prepareStatement("DELETE FROM users WHERE id = ?", Statement.RETURN_GENERATED_KEYS);
        ps.setLong(1, aLong);
        return ps;
    }

    @Override
    public PreparedStatement updateStatement(Connection connection, User entity) throws SQLException {
        PreparedStatement ps =  connection.prepareStatement("UPDATE users SET name = ?, password = ? WHERE id = ?", Statement.RETURN_GENERATED_KEYS);
        ps.setString(1, entity.getName());
        ps.setString(2, entity.getPassword());
        ps.setLong(3, entity.getId());
        return ps;
    }

    @Override
    public User createEntity(ResultSet rs) {
        try {
            Long id = rs.getLong("id");
            String username = rs.getString("username");
            String password = rs.getString("password");
            String type = rs.getString("type");
            if("ADMIN".equals(type)){
                return new Admin(id,username, password);
            }
            else {
                return new Cashier(id,username, password);
            }

        }
        catch (SQLException e) {
            throw new RepositoryException("Eroare la extragere user");
        }
    }

    @Override
    public Optional<User> getUserByUsername(String username) {
        String sql = "SELECT * FROM users WHERE username = ?";
        try(Connection con = getConnection(); PreparedStatement ps = con.prepareStatement(sql))
        {
            ps.setString(1, username);
            ResultSet rs = ps.executeQuery();
            if(rs.next()) {
                return Optional.of(createEntity(rs));
            }
        }
        catch (SQLException e) {
            throw new RepositoryException("Eroare la connessione user");
        }
        return Optional.empty();
    }
}

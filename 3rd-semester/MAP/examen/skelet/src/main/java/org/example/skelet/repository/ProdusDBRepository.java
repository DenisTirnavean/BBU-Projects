package org.example.skelet.repository;

import org.example.skelet.domain.entities.Produs;
import org.example.skelet.repository.exceptions.RepositoryException;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ProdusDBRepository extends DatabaseRepository<Long, Produs> implements ProdusRepository {
    public ProdusDBRepository(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    public PreparedStatement findOneStatement(Connection connection, Long aLong) throws SQLException {
        String sql = "SELECT * FROM produs WHERE produs.id = ?";
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setLong(1, aLong);
        return preparedStatement;
    }

    @Override
    public PreparedStatement findAllStatement(Connection connection) throws SQLException {
        String sql = "SELECT * FROM produs;";
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        return preparedStatement;
    }

    @Override
    public PreparedStatement saveStatement(Connection connection, Produs entity) throws SQLException {
        String sql = "INSERT INTO produs(sku, title, description, price, cantitate) VALUES(?, ?, ?, ?, ?)";
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setString(1, entity.getSku());
        preparedStatement.setString(2, entity.getTitle());
        preparedStatement.setString(3, entity.getDescription());
        preparedStatement.setFloat(4, entity.getPrice());
        preparedStatement.setInt(5, entity.getCantitate());
        return preparedStatement;
    }

    @Override
    public PreparedStatement deleteStatement(Connection connection, Long aLong) throws SQLException {
        String sql = "DELETE FROM produs WHERE produs.id = ?";
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setLong(1, aLong);
        return preparedStatement;
    }

    @Override
    public PreparedStatement updateStatement(Connection connection, Produs entity) throws SQLException {
        String sql = "UPDATE produs set sku=?, title=?, description=?, price=?, cantitate=? WHERE produs.id = ?";
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setString(1, entity.getSku());
        preparedStatement.setString(2, entity.getTitle());
        preparedStatement.setString(3, entity.getDescription());
        preparedStatement.setFloat(4, entity.getPrice());
        preparedStatement.setInt(5, entity.getCantitate());
        preparedStatement.setLong(6, entity.getId());
        return preparedStatement;
    }

    @Override
    public Produs createEntity(ResultSet rs) {
        try {
            Long id = rs.getLong("id");
            String sku = rs.getString("sku");
            String title = rs.getString("title");
            String description = rs.getString("description");
            float price = rs.getFloat("price");
            int cantitate = rs.getInt("cantitate");
            return new Produs(id, sku, title, description, price, cantitate);
        }
        catch (SQLException e) {
            throw new RepositoryException("Eroare la extragerea produsului");
        }
    }
}

import React from "react";
import "./PopupDelete.css";

const PopupDelete = ({ onClose, onDelete }) => {
  return (
    <div className="popup-delete-container">
      <div className="popup-delete-content">
        <h2>Are you sure?</h2>
        <p>Do you really want to delete your account? This process cannot be undone.</p>
        <div className="popup-delete-actions">
          <button onClick={onDelete} className="popup-delete-confirm">Delete Account</button>
          <button onClick={onClose} className="popup-delete-close">Close</button>
        </div>
      </div>
    </div>
  );
};

export default PopupDelete;

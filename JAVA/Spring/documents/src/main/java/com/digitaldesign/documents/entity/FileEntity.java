package com.digitaldesign.documents.entity;

import java.util.Set;

public class FileEntity {

    Set<UserEntity> permissionedUsers;
    String name;
    TypeOfFileEnum typeOfFile;
}

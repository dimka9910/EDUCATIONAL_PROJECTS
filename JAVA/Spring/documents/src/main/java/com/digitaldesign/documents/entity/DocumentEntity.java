package com.digitaldesign.documents.entity;

import java.util.Map;

public class DocumentEntity extends FileEntity{

    DocumentType documentType;
    PriorityEnum priority;
    String description;
    Map<Long, ConcreteDocument> versionsOfDocuments;
}

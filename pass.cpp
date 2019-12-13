try
{
// Connect to server on localhost
Session session(33060, "user", "password");

try
{
    Schema db = session.getSchema("test");

    // Use the collection 'my_collection'
    Collection myColl = db.getCollection("my_collection");

    // Find a document
    auto myDoc = myColl.find("name like :param").limit(1)
            .bind("param", "L%").execute();

    // Print document
    cout << myDoc.fetchOne() << endl;

    // Exit with success code
    exit(0);
}

catch (const Error &err)
{
cout << "The following error occurred: " << err << endl;
exit(1);
}

// Note: session is closed automatically when session object
// is destructed.
}

catch (const Error &err)
{
cout << "The database session could not be opened: " << err << endl;

// Exit with error code
exit(1);
}